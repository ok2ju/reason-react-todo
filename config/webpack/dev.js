const webpack = require('webpack')
const { resolve } = require('path')
const { config, plugins } = require('./base')

const webpackConfig = Object.assign({}, config, {
  mode: 'development',
  devtool: 'source-map',
  output: {
    filename: '[name].js',
    path: resolve(__dirname, 'devel'),
    publicPath: 'http://localhost:8882/'
  },
  plugins: [
    new webpack.HotModuleReplacementPlugin(),
    new webpack.DefinePlugin({
      'process.env': {
        'NODE_ENV': JSON.stringify('development')
      }
    }),
    ...plugins
  ],
  devServer: {
    contentBase: './devel',
    historyApiFallback: true,
    port: 8882,
    inline: true,
    hot: true
  }
})

module.exports = webpackConfig
