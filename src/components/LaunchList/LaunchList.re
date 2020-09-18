open LastLaunchesQuery;

[@react.component]
let make =
    (
      ~launches: array(option(LastLaunchesQuery.t_launchesPast)),
      ~handleShowDetails: option(string) => unit,
      ~display,
    ) => {
  <ul style={ReactDOM.Style.make(~display, ~padding="0", ())}>
    {launches
     ->Belt.Array.keepMap(launch => launch)
     ->Belt.Array.map(launch => {
         switch (launch.id) {
         | Some(id) => <li key=id> <Launch handleShowDetails launch /> </li>
         | None => React.null
         }
       })
     ->React.array}
  </ul>;
};
