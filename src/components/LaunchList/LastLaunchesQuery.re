[%graphql
  {|
    query LastLaunchesQuery($offset: Int) {
      launchesPast(limit: 20, offset: $offset) {
        mission_name
        launch_date_local
        links {
          flickr_images
        }
        id
        launch_success
      }
    }
  |}
];
