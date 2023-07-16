# Utilization Comment

This action comments the changes in utilization to a Pull Request 

## Inputs
_All paths are within the github workspace_

### `config_path`

The path to the config file for this action. The config file should be a .yml file. The action expects the top level key `bus_speed` with the speed of the CAN Bus in kHz. 

### `new_input_path`

Path to the CAN Data for the new branch (see below for expected format)

### `master_input_path`

The path to the artifact for the master branch. This should be a .json file, this action requires the message id as the top level key with a child key of "nominal" that contains the nominal usage over 0.1 seconds. Such as:

```json
{
  "0x60": {
    "nominal":"10.3000"
  }
}
```

## Outputs

### `comment`

This is the body of the comment to post. It will always include the invisible html comment `<!-- Utilization Comment -->` so it can be identified by bots reading it. 


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
- uses: ./.github/actions/utilization-comment
  id: comment
  with: 
    config_path: .github/utilization-config.yml
    new_input_path: branch/message-utilization.json
    master_input_path: master/message-utilization.json
```
The id is required to address the outputs in future steps.
You can run a specific version/branch by providing a sha to the checkout action. 