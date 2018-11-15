const webpack = require('webpack')

module.exports = {
  mode: 'production',
  entry: './lib/js/src/Main.bs.js',
  output: {
    path: __dirname + '/public',
    filename: 'bundle.js'
  }
}
