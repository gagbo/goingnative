var bindings = require('bindings')
var addon = bindings('myaddon')

const arg = process.argv[2]

//addon.print()
//addon.print_with_arg(arg)
console.log(addon.length(arg))
