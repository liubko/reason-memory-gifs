open Config;

open GiphyApiDecoder;

let reposUrl = "https://api.giphy.com/v1/gifs/trending?api_key=" ++ apiKey;

let fetchGifs = () =>
  Bs_fetch.fetch(reposUrl)
  |> Js.Promise.then_(Bs_fetch.Response.text)
  |> Js.Promise.then_(jsonText =>
       Js.Promise.resolve(parseGiphyResponseJson(Js.Json.parseExn(jsonText)))
     );