let graphqlEndpoint = "https://api.spacex.land/graphql/";
// let isLoggedIn =
//   switch (Dom.Storage.(localStorage |> getItem("token"))) {
//   | Some(_) => true
//   | None => false
//   };
// let headers = {
//   "authorization":
//     switch (Dom.Storage.(localStorage |> getItem("token"))) {
//     | Some(token) => token
//     | None => ""
//     },
// };

let link =
  ApolloClient.Link.HttpLink.make(
    ~uri=_ => graphqlEndpoint,
    (),
  );
let cache =
  ApolloClient.Cache.InMemoryCache.(
    make(
      ~typePolicies=[|
        (
          "Query",
          TypePolicy.make(
            ~fields=[|
              ("launchesPast", OffsetLimitPagination(KeySpecifier([|"limit","offset"|]))),
            |],
            (),
          ),
        ),
      |],
      (),
    )
  );
let client =
  ApolloClient.(
    make(
      ~cache,
      ~connectToDevTools=true,
      ~defaultOptions=
        DefaultOptions.make(
          ~mutate=
            DefaultMutateOptions.make(
              ~awaitRefetchQueries=true,
              ~errorPolicy=All,
              (),
            ),
          ~query=
            DefaultQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          ~watchQuery=
            DefaultWatchQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          (),
        ),
      ~link,
      (),
    )
  );

let default = client;
