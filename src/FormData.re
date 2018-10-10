type t = Fetch.formData;

[@bs.new] external formData: t = "FormData";

[@bs.send] external appendFile: (t, string, FileRe.File.t) => unit = "append";
[@bs.send] external appendString: (t, string, string) => unit = "append";

[@bs.send]
external get:
  (t, string) => [@bs.unwrap] [ | `File(FileRe.File.t) | `String(string)] =
  "get";

let make = () => formData;