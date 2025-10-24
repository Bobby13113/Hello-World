const http = require("http");

const PORT = 8081;

const server = http.createServer((req, res) => {
  res.writeHead(200, { "Content-Type": "text/plain" });
  res.end("Hello World from Node.js on Kubernetes!\n");
});

server.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
