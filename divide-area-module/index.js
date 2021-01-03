const testAddon = require('./build/Debug/addon.node');

console.log(testAddon.hello());

module.exports = testAddon;