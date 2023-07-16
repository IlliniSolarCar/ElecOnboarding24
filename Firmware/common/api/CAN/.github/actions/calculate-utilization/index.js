const core = require('@actions/core');
const github = require('@actions/github');
const fs = require('fs');
const yaml = require('js-yaml');


// most @actions toolkit packages have async methods
async function run() {
  try {
    core.info("Determining CAN Utilization!");

    //get context for what is going on and inputs
    core.startGroup("Set-Up");
    const context = github.context;
    core.debug("Context:");
    core.debug(context);

    core.info("Get Inputs and Config");
    const configPath = core.getInput('config_path', {required: true});
    const inputPath = core.getInput('input_path', {required: true});
    const outputPath = core.getInput('output_path', {required: true});


    configFile = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + configPath, 'utf8');
    configData = yaml.safeLoad(configFile);
    core.debug("Loaded Config:");
    core.debug(configData);

    core.info("Sum Overhead");
    overheadBits = 0;
    for (key in configData['overhead-bits']) {
      overheadBits += configData['overhead-bits'][key];
      core.debug("Overhead " + key + " is " + configData['overhead-bits'][key] + " bits.");
    }
    core.info("Overhead is " + overheadBits + " bits per message");

    core.endGroup();

    core.debug("Import Can Def");

    rawDef = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + inputPath);
    canDef = JSON.parse(rawDef);

    const messages = Object.keys(canDef);
    core.debug("Keys: ");
    core.debug(messages);

    core.info("Calculate Utilization for each ID");
    utilizations = {};

    messages.forEach((key, index) =>{
      largest = 8; //bits
      utilizations[key] = {};
      rate = canDef[key]["Interval"];
      utilizations[key]["rate"] = rate;
      size = 0;
      if(Array.isArray(canDef[key]["DataFormat"])){
        for (type of canDef[key]["DataFormat"]){
          size += configData['data-type-bits'][type]
          if(configData['data-type-bits'][type] > largest){
          	largest = configData['data-type-bits'][type];
          }
        }
      }else{
        size += configData['data-type-bits'][canDef[key]["DataFormat"]] * canDef[key]["DataQty"];
        largest = configData['data-type-bits'][canDef[key]["DataFormat"]];
      }
      utilizations[key]["bits"] = size = (Math.ceil(size/largest) * largest) + overheadBits;

      core.debug("Message " + key + " size of " + size + " bits every " + rate + "ms");

      
      if (rate > 0) {

        //Nominal
        utilizations[key]["nominal"] = (size * 100 / rate).toFixed(4);
        //Worst Case
        utilizations[key]["tenth-worst"] = (size * Math.ceil(100 / rate)).toFixed(4);
        utilizations[key]["full-worst"] = (size * Math.ceil(1000 / rate)).toFixed(4);

      }
      else{
        //Handle irregular messages
        //Nominal is none
        utilizations[key]["nominal"] = 0;
        //Worst Case we'll just include once
        utilizations[key]["tenth-worst"] = size;
        utilizations[key]["full-worst"] = size;
      }

      core.debug(utilizations[key]);

    });

    outputString = JSON.stringify(utilizations);
    fs.writeFileSync(process.env.GITHUB_WORKSPACE + "/" + outputPath, outputString, 'utf8');
    core.info("Wrote output to: " + outputPath);

  } catch (error) {
    core.setFailed(error.message);
  }
}

run();
