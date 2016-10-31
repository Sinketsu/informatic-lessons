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
      procedure dfs(ext_callback : TDFSCallback;
                    int_callback : TDFSCallback);
      function topological_sort : TStack<integer>;
      function get_linked_components_count : integer;
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

procedure TGraph.dfs(ext_callback : TDFSCallback;
                     int_callback : TDFSCallback);
var
  k, i : integer;
  checked : array of boolean;

  procedure local_dfs(i : integer; var checked : array of boolean; callback : TDFSCallback);
  var
    k : integer;
  begin
    checked[i] := true;

    for k := 0 to _vertex_count - 1 do
      if (_arr[i][k] <> 0) and (checked[k] = false) then
        local_dfs(k, checked, callback);

    callback(i);
  end;

begin

  setlength(checked, _vertex_count);
  for i := 0 to _vertex_count - 1 do
    checked[i] := false;

  for k := 0 to _vertex_count - 1 do
    if checked[k] = false then
    begin
      local_dfs(k, checked, int_callback);
      ext_callback(k);
    end;

end;

function TGraph.get_vertex_count: integer;
begin
  result := _vertex_count;
end;

function TGraph.topological_sort;
var
  i : integer;
  stack : TStack<integer>;

begin
  stack := TStack<integer>.Create;
  dfs(procedure (a : integer) begin end,
      procedure (a : integer) begin stack.push(a + 1); end);
  result := stack;
end;

function TGraph.get_linked_components_count;
var
  res : integer;
begin
  res := 0;
  dfs(procedure (a : integer) begin inc(res); end,
      procedure (a : integer) begin end);
  result := res;
end;


end.
