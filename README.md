# stel-duino
Stel-duino is a React app that runs on NodeJS; it's purpose is to serve as a dedicated testbed app, running in conjunction with [Stele](https://github.com/scimusmn/stele) and an Arduino sketch based on [arduino-base](https://github.com/scimusmn/arduino-base), to ensure that Arduino sketches properly interact with Stele and other SMM apps.

## Installation
First, you'll need to have `nodejs` installed on your computer; the instructions for doing this are outside the scope of this README, but you can read more [here](https://nodejs.org/en/download/).

Next, it is **highly** suggested you have `yarn` installed. After installing `nodejs`, you can run:
```
npm install yarn --global
```

Finally, make sure to clone this repo to your computer. You can do this one of two ways:

To clone the repo to your machine via the command line, run:

```
$ git clone https://github.com/scimusmn/stel-duino
```

If you'd rather not use the command line, go ahead and click the "[Download Button](https://github.com/scimusmn/stel-duino/archive/master.zip)" on the GitHub page to save the repo as a Zip file to your computer.

## Getting up and running
Once you've cloned the repo to your machine, you'll need to install the project dependencies. To do this navigate to the project root directory and run:

```
yarn
```

After the dependencies are installed, you can start the app by running:

```
npm run start
```
