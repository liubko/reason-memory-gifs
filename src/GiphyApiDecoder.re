let parseGiphyJson = (json: Js.Json.t) : Records.card => {
  /* todo: use uuid here */
  id: "",
  url:
    Json.Decode.at(["images", "fixed_height", "url"], Json.Decode.string, json),
  value: Json.Decode.field("id", Json.Decode.string, json),
  width:
    Json.Decode.at(
      ["images", "fixed_height", "width"],
      Json.Decode.string,
      json
    ),
  height:
    Json.Decode.at(
      ["images", "fixed_height", "height"],
      Json.Decode.string,
      json
    ),
  isGuesed: false
};

let parseGiphyResponseJson = json => {
  Js.log(json);
  Json.Decode.field("data", Json.Decode.list(parseGiphyJson), json)
  |> List.map((cardItem: Records.card) =>
       [
         {...cardItem, id: cardItem.value ++ "__a"},
         {...cardItem, id: cardItem.value ++ "__b"}
       ]
     )
  |> List.flatten;
};