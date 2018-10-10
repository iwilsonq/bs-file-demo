const path = require('path')

const isProd = process.env.NODE_ENV === 'production'
const buildPath = path.join(__dirname, 'build')

module.exports = {
  entry: {
    index: './lib/js/src/Index.bs.js'
  },
  mode: isProd ? 'production' : 'development',
  output: {
    path: buildPath,
    filename: '[name].js'
  }
}
