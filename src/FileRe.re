module File = {
  type t;

  [@bs.new]
  external file:
    (~bits: array(Js.Typed_array.array_buffer), ~name: string) => t =
    "File";

  let make = (~bits, ~name) => file(~bits, ~name);
};

module FileReader = {
  type t;
  [@bs.new] external fileReader: t = "FileReader";

  [@bs.set] external setOnload: (t, [@bs.this] (t => unit)) => unit = "onload";

  [@bs.get] external getResult: t => string = "result";

  [@bs.send] external readAsDataURL: (t, File.t) => unit = "";

  let make = () => fileReader;
};