[%bs.raw {|require("./LaunchDetails.css")|}];

module LaunchQuery = [%graphql
  {|
    query LaunchQuery( $id: ID! ) {
        launch(id:$id) {
            mission_name
            launch_year
            launch_success
            launch_date_local,
            rocket {
                rocket_name
                rocket_type
            }
            links {
                flickr_images
            }
        }
    }
|}
];

[@react.component]
let make = (~id, ~handleShowDetails: option(string) => unit) => {
  let variables: LaunchQuery.t_variables = {
    id: id->Belt.Option.getWithDefault(""),
  };
  let result =
    ApolloClient.React.useQuery(~query=(module LaunchQuery), variables);
  // both work
  // let result = LaunchQuery.use({id: id->Belt.Option.getWithDefault("")});

  switch (result) {
  | {loading: true} =>
    <h1
      style={ReactDOM.Style.make(
        ~color="white",
        ~fontSize="10rem",
        ~height="100vw",
        (),
      )}>
      "Loading..."->React.string
    </h1>
  | {
      data:
        Some({
          launch:
            Some({
              links,
              mission_name,
              launch_year,
              launch_success,
              launch_date_local,
              rocket,
            }),
        }),
    } =>
    let missionName =
      switch (mission_name) {
      | Some(name) => name
      | None => ""
      };
    let launch_year =
      switch (launch_year) {
      | Some(launch_year) => launch_year
      | None => ""
      };
    let launch_success =
      switch (launch_success) {
      | Some(launch_success) => launch_success
      | None => false
      };
    let launch_date_local =
      switch (launch_date_local) {
      | Some(launch_date_local) =>
        Js.Json.decodeString(launch_date_local)
        ->Belt.Option.getWithDefault("")
        ->React.string
      | None => React.null
      };

    let rocketInfo =
      switch (rocket) {
      | Some(rocket) =>
        switch (rocket.rocket_name, rocket.rocket_type) {
        | (Some(name), Some(rocketType)) =>
          <>
            <h2> name->React.string </h2>
            <h3> rocketType->React.string </h3>
          </>
        | _ => React.null
        }
      | None => React.null
      };
    let images =
      switch (links) {
      | Some(links) =>
        switch (links.flickr_images) {
        | Some(images) =>
          let images = images->Belt.Array.keepMap(i => Some(i));
          let links = images->Belt.Array.keepMap(i => i);
          links
          ->Belt.Array.map(link => <img src=link alt="lol" />)
          ->React.array;

        | None => React.null
        }
      | None => React.null
      };

    <div className="launch-details-container">
      <h1> missionName->React.string </h1>
      <h4>
        {"Launch Year: "
         ++ {
           launch_year;
         }
         |> React.string}
      </h4>
      <h4>
        {"Successful: " ++ string_of_bool(launch_success) |> React.string}
      </h4>
      <h4> launch_date_local </h4>
      rocketInfo
      <button className="back-button" onClick={_ => handleShowDetails(None)}>
        "Back"->React.string
      </button>
      <div className="img-container"> images </div>
    </div>;
  | _ => React.null
  };
};
