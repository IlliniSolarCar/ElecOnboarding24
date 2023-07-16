const core = require('@actions/core');
const github = require('@actions/github');
const fs = require('fs');
const yaml = require('js-yaml');

commentString = "<!-- Utilization Comment -->"

async function newLine(count) {
  do {
    commentString += "<br>";
    count--;
  }
  while (count > 0);
};

async function line(text) {
  commentString += text;
  await newLine(1);
};

async function header(column1, column2, column3) {
  commentString += '<table style="width:100%">';
  commentString += '<tr><th>'+column1+'</th><th>'+column2+'</th><th>'+column3+'</th></tr>'; 
};

async function row(column1, column2, column3) {
  commentString += '<tr><td>'+column1+'</td><td>'+column2+'</td><td>'+column3+'</td></tr>'; 
};

async function endTable() {
  commentString += '</table>';
  await newLine(1);
};

// most @actions toolkit packages have async methods
async function run() {
  try {
    core.info("Creating the Utilization Comment");

    //get context for what is going on and inputs
    core.startGroup("Set-Up");
    const context = github.context;
    core.debug("Context:");
    core.debug(context);

    //process.env.GITHUB_WORKSPACE = '/home/jonathan/repos/personal/CAN';
    const configPath = core.getInput('config_path', {required: true});
    const newInputFile = core.getInput('new_input_path', {required: true});
    const masterInputFile = core.getInput('master_input_path', {required: true});
/*
    const configPath = '.github/utilization-config.yml';
    const newInputFile = 'message-utilization.json';
    const masterInputFile = 'message-utilization-master.json' */
    //load Config
    configFile = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + configPath, 'utf8');
    configData = yaml.safeLoad(configFile);
    core.debug("Loaded Config");
    const speed = configData['bus_speed'];
    core.debug("Speed (kHz) is: " + speed);

    //read old and new jsons
    newMessageFile = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + newInputFile, 'utf8');
    newCanData = JSON.parse(newMessageFile);
    core.debug("Loaded New Can Data:");
    core.debug(newCanData);

    oldMessageFile = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + masterInputFile, 'utf8');
    oldCanData = JSON.parse(oldMessageFile);
    core.debug("Loaded Old Can Data:");
    core.debug(oldCanData);

    const oldMessages = Object.keys(oldCanData);
    const newMessages = Object.keys(newCanData);

    core.endGroup();

    //Start Comment
    await line("Here's how this PR changes the utilization on the CAN Bus  :chart_with_upwards_trend:");
    await line("<i>Comment last updated for commit: " + context.payload.pull_request.head.sha.slice(0,7) + "</i>")
    await newLine(1);
    await header("Message","Previous bits/s","New bits/s");
    
    netChange = 0;
    totalChanged = 0;

    //add Removed Messages
    oldMessages.forEach((key, index) =>{
      if(!(newMessages.includes(key))){
        row(key, parseFloat(oldCanData[key]["nominal"]) * 10, "Removed");
        netChange -= parseFloat(oldCanData[key]["nominal"]) * 10;
        totalChanged++;
      }
    });

    //add changed messages
    newMessages.forEach((key, index) =>{
      if(oldMessages.includes(key)){
        if(oldCanData[key]["nominal"] != newCanData[key]["nominal"]){
          row(key, parseFloat(oldCanData[key]["nominal"]) * 10, parseFloat(newCanData[key]["nominal"]) * 10);
          netChange += (parseFloat(newCanData[key]["nominal"]) - parseFloat(oldCanData[key]["nominal"])) * 10;
          totalChanged++;
        }
      }
      else
      {
        row(key, "New Message", parseFloat(newCanData[key]["nominal"]) * 10);
        netChange += parseFloat(newCanData[key]["nominal"]) * 10;
        totalChanged++;
      }
    });
    //add new messages
    if(totalChanged == 0){
      await row("No messages changed", "n/a", "n/a");
    }
    await endTable();

    //Net Change
    await line("<b>" + totalChanged + "</b> Messages Changed for a net change of: <i>" + netChange + " bits per second</i>");
    const netChangePercent = (netChange / (speed * 1000) * 100).toFixed(2);
    if(netChangePercent > 0.00){
      await line("The nominal utilization will increase by: <b>" + netChangePercent + "%</b> on a " + speed + "kHz bus");
    }
    else if(netChangePercent < 0.00){
      await line("The nominal utilization will decrease by: <b>" + Math.abs(netChangePercent) + "%</b> on a " + speed + "kHz bus");
    }
    else{
      await line("There is no significant change to nominal percent utilization");
    }

    await newLine(1);


    //Set as an output
    core.setOutput("comment", commentString);

  } catch (error) {
    core.setFailed(error.message);
  }
}

run();
