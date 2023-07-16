# Sum For Badges

This actions turns the bit/s usage of each message into a utilization percent for each context. It provides this information as an output as well as respective badge colors. 

## Inputs
_All paths are within the github workspace_

### `config_path`

The path to the config file for this action. The config file should be a .yml file. The action expects:
- top level key `bus_speed` with the speed of the CAN Bus in kHz
- top level key `debug_messages` with the following child keys:
     - `min`: The ID of the lowest debug message
     - `max`: The ID of the highest debug message
     - _Messages between these values, inclusive, will not be included in the no debug sums_ 
     - _Note: if there are no debug messages set min higher than max_
- top level key `color` with child keys: 
     - `critical`: The utilization percent above which to color as critical (red)
     - `warn`: The utilization percent above which to color as a warning (yellow)
     - _Else will be green_

For example:

```yaml
bus_speed: 500
debug_messages:
  min: 0x400
  max: 0x4FF
colors:
  critical: 50 
  warn: 30
```

### `input_path`


The path to the file with the CAN Bus Data. This should be a .json file, this action requires the message id as the top level key with the following child keys and information:

```json
{
  "0x60": {
    "nominal":"10.3000",
    "tenth-worst":"103.0000",
    "full-worst":"103.0000"
  }
}
```

## Outputs

This action has the following outputs for each badge:
- String for the right side of the badge, the percent to two decimal points such as `10.22%`
- Hex Color for the right side of the badge, such as `#228B22` (green)

Specifically they are named:

### `nominal`
### `nominalColor`
### `tenthWorst`
### `tenthWorstColor`
### `fullWorst`
### `fullWorstColor`
### `nominalNoDebug`
### `nominalNoDebugColor`
### `tenthWorstNoDebug`
### `tenthWorstNoDebugColor`
### `fullWorstNoDebug`
### `fullWorstNoDebugColor`



# Development

## Run Locally

1. Install the dependencies

```bash
npm install
```

2. Hardcode the inputs to your test files/paths

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
- uses: /.github/actions/sum-for-badges
  id: totals
  with:
    config_path: .github/utilization-config.yml
    input_path: /message-utilization.json
```
The id is required to address the outputs in future steps.
You can run a specific version/branch by providing a sha to the checkout action. 