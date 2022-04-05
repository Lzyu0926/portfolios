const soap = require('soap');
const http = require('http');
const xml = require('fs').readFileSync('AddMul.wsdl', 'utf8'); // 讀入 adder.wsdl 描述檔 存到xml
const service = {
    CalculatorImplService: {
        CalculatorImplPort: {
            add: function (args) { //傳入參數
                return {result: args.x + args.y}; //將參數的 x y 相加並回傳
            },
            multiply: function(args) {
                return {result: args.x * args.y};
            }

        } 
    }
};

const server = http.createServer(function (request, response) {
    response.end('404: Not Found: ' + request.url);
});

soap.listen(server, '/AddMul', service, xml, function () { 
    console.log('server initialized');
});

server.listen(8192);  
