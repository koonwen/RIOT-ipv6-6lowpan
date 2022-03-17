open Tcpip.Ip

external mirage_riot_get_ip : unit -> Cstruct.t = "mirage_riot_get_ip"

type nonrec error = private [> error ]

let pp_error : error Fmt.t = failwith ""

type ipaddr = int Array.t

let pp_ipaddr : ipaddr Fmt.t = failwith ""

type t = { addr : ipaddr; proto : proto }

let disconnect : t -> unit Lwt.t = failwith ""

type callback = src:ipaddr -> dst:ipaddr -> Cstruct.t -> unit Lwt.t

let input :
    t ->
    tcp:callback ->
    udp:callback ->
    default:(proto:int -> callback) ->
    Cstruct.t ->
    unit Lwt.t =
  failwith ""

let write :
    t ->
    ?fragment:bool ->
    ?ttl:int ->
    ?src:ipaddr ->
    ipaddr ->
    proto ->
    ?size:int ->
    (Cstruct.t -> int) ->
    Cstruct.t list ->
    (unit, error) result Lwt.t =
  failwith ""

let pseudoheader : t -> ?src:ipaddr -> ipaddr -> proto -> int -> Cstruct.t =
  failwith ""

let src : t -> dst:ipaddr -> ipaddr = failwith ""
let get_ip : t -> ipaddr list = [ t.addr ]
let mtu : t -> dst:ipaddr -> int = failwith ""
