unit Graph;

interface

uses
  System.SysUtils, System.Generics.Defaults, System.Generics.Collections;

type
  TDFSCallback = reference to procedure (a : integer);

  TGraph = class
    private
      _arr : array of array of integer;
      _list : TObject;
      _vertex_count : integer;

    public
      constructor Create(vertex_count : integer);
      function get_vertex_count() : integer;
      procedure add_link(from, where : integer);
      procedure dfs(i : integer; var checked : array of boolean; callback : TDFSCallback);
      function topological_sort : TStack<integer>;
  end;

implementation

  constructor TGraph.Create(vertex_count : integer);
  var
    i, k: Integer;
  begin
    SetLength(_arr, vertex_count, vertex_count);
    _vertex_count := vertex_count;

    for i := 0 to _vertex_count - 1 do
      for k := 0 to _vertex_count - 1 do
        _arr[i][k] := 0;

  end;

  procedure TGraph.add_link(from: Integer; where: Integer);
  begin
    _arr[from - 1][where - 1] := 1;
  end;

  procedure TGraph.dfs(i : integer; var checked : array of boolean; callback : TDFSCallback);
  var
    k : integer;
  begin
    checked[i] := true;

    for k := 0 to _vertex_count - 1 do
      if (_arr[i][k] <> 0) and (checked[k] = false) then
        dfs(k, checked, callback);

    callback(i);
  end;

  function TGraph.get_vertex_count: integer;
  begin
    result := _vertex_count;
  end;

  function TGraph.topological_sort;
  var
    checked : array of boolean;
    i : integer;
    stack : TStack<integer>;

  begin
    stack := TStack<integer>.Create;
    SetLength(checked, _vertex_count);
    for i := 0 to _vertex_count - 1 do
      checked[i] := false;

    for i := 0 to _vertex_count - 1 do
      if checked[i] = false then
        dfs(i, checked, procedure (a : integer) begin stack.push(a + 1); end);
    result := stack;

  end;

end.
