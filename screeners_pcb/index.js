var noble = require('noble');
var osc = require('osc');

noble.on('stateChange', function(state) {
  if (state === 'poweredOn') {
    noble.startScanning();
    console.log('scanning...');
  } else {
    noble.stopScanning();
    console.log('not scanning...');
  }
});

noble.on('discover', function(peripheral) {
  var uuid = '6e57d0876e3d451e923c8909995031fc';
  if (peripheral.id === uuid || peripheral.address === uuid) {
    console.log('found RFchino');
    noble.stopScanning();

    peripheral.connect(function(err) {
      console.log('connected to RFchino');

      peripheral.discoverServices(['2220'], function(err, services) {
        console.log('found service:', services[0].uuid);

        services[0].discoverCharacteristics(['2222'], function(err, characteristics) {
          console.log('found characteristic:', characteristics[0].uuid);
          // characteristic = characteristics[0];

          var stdin = process.openStdin();
          stdin.addListener("data", function(d) {
            toggleGlass(characteristics[0], d.toString().trim());
          });

        });
      });
    });
  }
});

var toggleGlass = function(characteristic, num){
  const buf1 = new Buffer(num, 'utf-8');
  characteristic.write(buf1, false, function(err, data){
    
  });
}

// var udpPort = new osc.UDPPort({
//     localAddress: "0.0.0.0",
//     localPort: 57121
// });

// udpPort.on('ready', function(){
//   console.log("Listening for OSC over UDP.");
// });

// udpPort.on("message", function (oscMessage) {
//   console.log(oscMessage);
// });

// udpPort.on("error", function (err) {
//     console.log(err);
// });

// udpPort.open();