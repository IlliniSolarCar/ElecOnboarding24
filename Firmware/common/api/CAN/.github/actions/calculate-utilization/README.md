# Calculate Message Utilization

This action calculates the utilization (in bits per time unit) of each message provided in the CAN Def. It creates a JSON file with this information for use in future actions. 

## Inputs
_All paths are within the github workspace_

### `input_path`

This is the path where the CAN Def is located. Will fail if CAN Def does not meet the spec. 

### `output_path`

The path to put the artifact json file at. 

### `config_path`

The path to the config file for this action. The config file should be a .yml file. The action expects the top level key `overhead-bits` with child keys that are overhead parts of the message and how many bits they are as shown below. It will sum all child keys of `overhead-bits`.
```yaml
overhead-bits:
  crc: 15
  EOF: 7
```
It also expects the top level key `data-type-bits`. Each data type used on the bus needs to be a child key of `data-type-bits` with the number of bits that data type is. Such as:
```yaml
data-type-bits:
  FloatLE: 32
  Uint64LE: 64
```

## Output File

This action generates a json file with the following information for each message:
* rate
* bits per message
* nominal usage (bits per 0.1s)
* Worst Case Usage over 0.1s
* Worst Case Usage over 1s

Worst case usage rounds up to the nearest whole number of messages, for example a message sent every 0.25 seconds would be sent 1 time in 0.1s worst case and 4 in 1s. All are the usages are rounded to 4 decimal places. Irregular messages are not included in the nominal usage and are included once in the worst case usage. 

It will be formatted with the message as the key as follows:
```json
{
  "0x60": {
    "rate":1000,
    "bits":103,
    "nominal":"10.3000",
    "tenth-worst":"103.0000",
    "full-worst":"103.0000"
  }
}
```

# Development

Since this action can create large artifacts (in terms of human readability) I recommend creating a smaller test canDef that includes a cross section of the things you want to test so it is easier to verify. 

## Run Locally

1. Install the dependencies

```bash
npm install
```

2. Hardcode the inputs

3. `node index.js`


## To Make Changes

GitHub Actions will run the entry point from the action.yml. Packaging assembles the code into one file that can be checked in to Git, enabling fast and reliable execution and preventing the need to check in node_modules.

Actions are run from GitHub repos.  Packaging the action will create a packaged action in the dist folder.

Run prepare

```bash
npm run prepare
```

Since the packaged index.js is run from the dist folder.

```bash
git add dist
```
Be sure to update the `action.yml` if there is a change to the inputs/output or how this is run!

## Usage

```yaml
- uses: actions/checkout@v2
- uses: /.github/actions/calculate-utilization
  with:
    config_path: .github/utilization-config.yml
    input_path: canDef.json
    output_path: message-utilization.json
```
You can run a specific version/branch by providing a sha to the checkout action. 