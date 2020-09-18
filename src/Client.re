let graphqlEndpoint = "https://api.spacex.land/graphql/";

let link = ApolloClient.Link.HttpLink.make(~uri=_ => graphqlEndpoint, ());
let cache =
  ApolloClient.Cache.InMemoryCache.(
    make(
      ~typePolicies=[|
        (
          "Query",
          TypePolicy.make(
            ~fields=[|
              (
                "launchesPast",
                OffsetLimitPagination(KeySpecifier([|"limit", "offset"|])),
              ),
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
