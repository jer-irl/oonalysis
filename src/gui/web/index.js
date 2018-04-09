
let ws = new WebSocket("ws://localhost:54321");
ws.onopen = function() {

    new QWebChannel(ws, function(channel) {
        // make dialog object accessible globally
        let api = channel.objects.state;

        api.doExit();
    });
};
