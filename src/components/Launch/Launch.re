[%bs.raw {|require("./Launch.css")|}];
open LastLaunchesQuery;

[@react.component]
let make =
    (
      ~launch: LastLaunchesQuery.t_launchesPast,
      ~handleShowDetails: option(string) => unit,
    ) => {
  Js.log2("LAUNCH", launch);
  let flickr_images =
    switch (launch.links) {
    | Some(links) =>
      switch (links.flickr_images) {
      | Some(images) =>
        images->Belt.Array.keepMap(
          fun
          | Some(flickr_images) => Some(flickr_images)
          | _ => None,
        )
      | None => [||]
      }
    | None => [||]
    };

  <div className="card-container">
    <img className="launch-img" src={Array.get(flickr_images, 0)} alt="" />
    <div className="mission-info">
      {launch.mission_name
       ->Belt.Option.map(mission_name =>
           <span className="mission-name"> mission_name->React.string </span>
         )
       ->Belt.Option.getWithDefault(React.null)}
      {launch.launch_date_local
       ->Belt.Option.map(launch_date_local => {
           let date =
             Js.Json.decodeString(launch_date_local)
             ->Belt.Option.getWithDefault("");
           <span className="launch-date">
             {"Launch Date:" ++ date |> React.string}
           </span>;
         })
       ->Belt.Option.getWithDefault(React.null)}
      {launch.id
       ->Belt.Option.map(id =>
           <button
             className="show-details-button"
             onClick={_ => handleShowDetails(Some(id))}>
             "Show Details"->React.string
           </button>
         )
       ->Belt.Option.getWithDefault(React.null)}
      {launch.launch_success
       ->Belt.Option.map(launch_success =>
           <h2
             style={ReactDOM.Style.make(
               ~color=launch_success ? "green" : "red",
               (),
             )}
             className="launch-success">
             {launch_success ? "Success" : "Fail"}->React.string
           </h2>
         )
       ->Belt.Option.getWithDefault(React.null)}
    </div>
  </div>;
};
