const core = require('@actions/core');
const github = require('@actions/github');
const fs = require('fs');
const yaml = require('js-yaml');

// most @actions toolkit packages have async methods
async function run() {
  try {
    core.info("Setting up for badges");

    //get context for what is going on and inputs
    core.startGroup("Set-Up");
    const context = github.context;
    core.debug("Context:");
    core.debug(context);

    core.info("Get Speed");
    const configPath = core.getInput('config_path', {required: true});
    const inputFile = core.getInput('input_path', {required: true});

    configFile = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + configPath, 'utf8');
    configData = yaml.safeLoad(configFile);
    core.debug("Loaded Config:");
    core.debug(configData);

    const speed = configData['bus_speed'];
    const minDebug = configData['debug_messages']['min'];
    const maxDebug = configData['debug_messages']['max'];
    const maxBitsPerSecond = speed * 1000;
    core.info("Max Bits per second: " + maxBitsPerSecond);
    core.info("Debug Messages from: " + minDebug + " - " + maxDebug);


    messageFile = fs.readFileSync(process.env.GITHUB_WORKSPACE + "/" + inputFile, 'utf8');
    canData = JSON.parse(messageFile);
    core.debug("Loaded Can Data:");
    core.debug(canData);

    core.endGroup();


    const messages = Object.keys(canData);
    core.debug("Keys: ");
    core.debug(messages);

    core.info("Calculate Utilization Percent for each ID");

    outputs = {};
    outputs['nominal'] = {};
    outputs['tenthWorst'] = {};
    outputs['fullWorst'] = {};
    outputs['nominalNoDebug'] = {};
    outputs['tenthWorstNoDebug'] = {};
    outputs['fullWorstNoDebug'] = {};

    outputs['nominal']['sum'] = 0;
    outputs['tenthWorst']['sum'] = 0;
    outputs['fullWorst']['sum'] = 0;
    outputs['nominalNoDebug']['sum'] = 0;
    outputs['tenthWorstNoDebug']['sum'] = 0;
    outputs['fullWorstNoDebug']['sum'] = 0;

    messages.forEach((key, index) =>{

      outputs['nominal']['sum'] += parseFloat(canData[key]["nominal"]);
      outputs['tenthWorst']['sum'] += parseFloat(canData[key]["tenth-worst"]);
      outputs['fullWorst']['sum'] += parseFloat(canData[key]["full-worst"]);

      if( key < minDebug || key > maxDebug )
      {
        outputs['nominalNoDebug']['sum'] += parseFloat(canData[key]["nominal"]);
        outputs['tenthWorstNoDebug']['sum'] += parseFloat(canData[key]["tenth-worst"]);
        outputs['fullWorstNoDebug']['sum'] += parseFloat(canData[key]["full-worst"]);
      }
    });

    core.debug("Nominal Total: " + outputs['nominal']['sum']);
    core.debug("Tenth Second Worst Case Total: " + outputs['tenthWorst']['sum']);
    core.debug("Full Second Worst Case Total: " + outputs['fullWorst']['sum']);
    core.debug("Nominal Total No Debug: " + outputs['nominalNoDebug']['sum']);
    core.debug("Tenth Second Worst Case Total No Debug: " + outputs['tenthWorstNoDebug']['sum']);
    core.debug("Full Second Worst Case Total No Debug: " + outputs['fullWorstNoDebug']['sum']);

    const sums = Object.keys(outputs);

    sums.forEach((key, index) =>{
      divisor = 10;
      if(key == 'fullWorstNoDebug' || key == 'fullWorst')
      {
        divisor = 1;
      }

      outputs[key]['percent'] = (outputs[key]['sum'] / (maxBitsPerSecond / divisor) * 100).toFixed(2);

      if(outputs[key]['percent'] >= configData['colors']['critical'])
      {
        outputs[key]['color'] = '#FD0E35';
      }
      else if(outputs[key]['percent'] >= configData['colors']['warn'])
      {
        outputs[key]['color'] = '#FEFE22';
      }
      else
      {
        outputs[key]['color'] = '#228B22';
      }

      core.info(key + " Usage: " + outputs[key]['percent'] + "% Color: " + outputs[key]['color']);
      core.setOutput(key, outputs[key]['percent'] + "%");
      core.setOutput(key + "Color", outputs[key]['color']);

    });
  } catch (error) {
    core.setFailed(error.message);
  }
}

run();
