let str = ReasonReact.string;

open FileRe;

type state = {files: array(File.t)};

type action =
  | ChangeFile(File.t)
  | Upload;

let component = ReasonReact.reducerComponent("BsFileDemo");
let make = _children => {
  let changeFile = (event, self) => {
    let files = ReactEvent.Form.target(event)##files;
    self.ReasonReact.send(ChangeFile(files[0]));
  };
  let upload = (_event, self) => self.ReasonReact.send(Upload);
  {
    ...component,
    initialState: () => {files: [||]},
    reducer: (action, state) =>
      switch (action) {
      | ChangeFile(file) => ReasonReact.Update({files: [|file|]})
      | Upload =>
        Js.log("upload");
        let data = FormData.make();
        FormData.appendFile(data, "avatar", state.files[0]);
        FormData.appendString(data, "filename", "santaduck");

        Js.log(FormData.get(data, "avatar"));
        Js.log(FormData.get(data, "filename"));

        Js.Promise.(
          Fetch.fetchWithInit(
            "http://localhost:8080/profile",
            Fetch.RequestInit.make(
              ~method_=Post,
              ~body=Fetch.BodyInit.makeWithFormData(data),
              (),
            ),
          )
          |> then_(Fetch.Response.json)
          |> ignore
        );
        ReasonReact.Update({files: [||]});
      },
    render: ({state, handle}) => {
      Js.log(state);
      <div>
        <h1> {"bs-file" |> str} </h1>
        <p> {"open the console (CMD + C) to view logs" |> str} </p>
        <input type_="file" onChange={handle(changeFile)} />
        <div id="preview" />
        <button onClick={handle(upload)}> {"Upload" |> str} </button>
      </div>;
    },
  };
};