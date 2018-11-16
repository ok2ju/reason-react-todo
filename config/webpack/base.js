const webpack = require('webpack')
const { resolve } = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')

const dir = {
  build: resolve(__dirname, '..', '..', 'build')
}

const config = {
  entry: {
    bundle: './lib/js/src/Main.bs.js'
  }
}

const plugins = [
  new webpack.NamedModulesPlugin(),
  new HtmlWebpackPlugin({
    filename: 'index.html',
    template: 'src/index.ejs',
    title: 'Reason React Todo'
  })
]

module.exports = {
  dir,
  config,
  plugins
}
