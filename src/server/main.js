var net = require('net');

var Update = function(updateId, args) {
    this.updateId = updateId;
    this.args = args;
};
Update.prototype.magic = function() {
    return 0x42;
};
Update.prototype.length = function() {
    // Length of args plus one for the command
    return this.args.length + 1;
};
Update.prototype.toArray = function() {
    return [this.magic(), this.length(), this.updateId].concat(this.args);
};
Update.prototype.toBuffer = function() {
    return new Buffer(new Uint8Array(this.toArray()));
};

var server = net.createServer(function(client) {
    client.on('end', function() {
        console.log('Client disconnected');
    });
    client.on('close', function() {
        console.log('Client socket closed');
    });

    client.on('data', function(data) {
        console.log('Got data from client; data=', data);

        var update = new Update(0x0, [100, 50, 255, 255, 255]);
        client.write(update.toBuffer());
    });

    console.log('New client connected');
});

server.listen(1234);
