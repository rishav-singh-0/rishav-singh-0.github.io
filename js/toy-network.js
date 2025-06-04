// define the data for the network
const data = {
    nodes: [
        // ...
    ],
    edges: [
        // ...
    ]
};

// define the network options
const options = {
    width: "100%",
    height: "500px"
};

// create a network
const container = document.getElementById("mynetwork");
//const options = {};
const network = new vis.Network(container, data, options);

// define the node styles
const nodeStyles = {
    nodes: {
        shape: "box",
        color: {
            background: "#f5f5f5",
            highlight: {
                background: "#e0e0e0"
            }
        },
        borderWidth: 1,
        borderWidthSelected: 2,
        font: {
            color: "#333"
        }
    }
};

// fetch the data from the JSON files
Promise.all([
    fetch("/data/toy-network/nodes.json"),
    fetch("/data/toy-network/edges.json")
])
.then(([nodesResponse, edgesResponse]) => Promise.all([
    nodesResponse.json(),
    edgesResponse.json()
]))
.then(([nodesData, edgesData]) => {
    // combine the nodes and edges data
    const data = {
        nodes: nodesData,
        edges: edgesData
    };

    // update the data in the network
    network.setData(data);

    // apply the node styles
    network.setOptions(nodeStyles);
});
