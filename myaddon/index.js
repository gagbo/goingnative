var bindings = require('bindings')
var addon = bindings('myaddon')

const arg1 = process.argv[2]

// addon.print()
// addon.print_with_arg(arg1)
// console.log(addon.length(arg1))

// const callback = () => {console.log("Done!")}
// addon.delay(arg1, callback)

var interval = setInterval(function () {
  process.stdout.write('.')
}, 50)

addon.delay(process.argv[2], function () {
  clearInterval(interval)
  console.log('Done!')
})

process.stdout.write('Waiting')
