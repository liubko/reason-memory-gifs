[@bs.module] external uuidv4 : unit => string = "uuid/v4";

[@bs.val] external random : unit => float = "Math.random";

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
  let gifs =
    Json.Decode.field("data", Json.Decode.array(parseGiphyJson), json);
  let gifsWithPairs =
    gifs
    |> Array.append(gifs)
    |> Array.map((gif: Records.card) => {...gif, id: uuidv4()});
  Array.sort((_, _) => compare(0.5 -. random(), 0.0), gifsWithPairs);
  gifsWithPairs;
};