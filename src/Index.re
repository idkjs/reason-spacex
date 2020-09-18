[%bs.raw {|require('./index.css')|}];
[@bs.module "./serviceWorker"]
external register_service_worker: unit => unit = "register";
[@bs.module "./serviceWorker"]
external unregister_service_worker: unit => unit = "unregister";

ReactDOMRe.renderToElementWithId(
  <ApolloClient.React.ApolloProvider client=Client.client>
    <App />
  </ApolloClient.React.ApolloProvider>,
  "root",
);
unregister_service_worker();
