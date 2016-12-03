
var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);

Pebble.addEventListener('webviewclosed', function(e) {
  var dict = clay.getSettings(e.response);
console.log(JSON.stringify(dict));
});
