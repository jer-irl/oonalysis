let api;

function showInclusions() {
    const svg = d3.select('.target').append('svg');
    const dots = svg.selectAll('.dot')
        .data([1, 2, 3, 4])
        .enter().append('circle')
        .attr('class', 'dot')
        .attr('r', 10)
        .attr('cy', 20)
        .attr('cx', d => d);

}

let ws = new WebSocket("ws://localhost:54321");
ws.onopen = function() {

    new QWebChannel(ws, function(channel) {
        api = channel.objects.interface;

        api.requestInclusions(() => {
            console.log('here1');
        });
    });
};
