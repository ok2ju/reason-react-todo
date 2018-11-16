const webpack = require('webpack')
const UglifyJsPlugin = require('uglifyjs-webpack-plugin')
const { dir, config, plugins } = require('./base')

const webpackConfig = Object.assign({}, config, {
  mode: 'production',
  stats: true,
  devtool: 'cheap-module-source-map',
  output: {
    filename: 'scripts/[name].[chunkhash:8].js',
    path: dir.build,
    publicPath: '/'
  },
  plugins: [
    ...plugins,
    new webpack.DefinePlugin({
      'process.env': {
        'NODE_ENV': JSON.stringify('production')
      }
    }),
    new UglifyJsPlugin({
      sourceMap: true,
      uglifyOptions: {
        output: {
          comments: false,
          beautify: false
        }
      }
    })
  ]
})

module.exports = webpackConfig
