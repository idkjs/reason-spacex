// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var App = require("./App.bs.js");
var React = require("react");
var Client = require("./Client.bs.js");
var ReactDOMRe = require("reason-react/src/legacy/ReactDOMRe.bs.js");
var Client$1 = require("@apollo/client");
var ServiceWorker = require("./serviceWorker");

((require('./index.css')));

function register_service_worker(prim) {
  ServiceWorker.register();
  
}

function unregister_service_worker(prim) {
  ServiceWorker.unregister();
  
}

ReactDOMRe.renderToElementWithId(React.createElement(Client$1.ApolloProvider, {
          client: Client.client,
          children: React.createElement(App.make, {})
        }), "root");

ServiceWorker.unregister();

exports.register_service_worker = register_service_worker;
exports.unregister_service_worker = unregister_service_worker;
/*  Not a pure module */
