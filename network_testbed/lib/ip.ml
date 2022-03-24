open Tcpip.Ip
open Riot

(* external mirage_riot_get_ip : unit -> Cstruct.t = "mirage_riot_get_ip" *)
[%%cstruct
type ip_hdr_t = {
  v_tc_fl : uint16_t; [@len 1] (*Big endian*)
  len : uint16_t; [@len 1] (*Big endian*)
  ulpl : uint8_t; [@len 1]
  nh : uint8_t; [@len 1]
  hl : uint8_t; [@len 1]
  src : uint8_t; [@len 16]
  dst : uint8_t; [@len 16]
}
[@@big_endian]]

type nonrec error = private [> error ]

let pp_error : error Fmt.t = failwith "pp_error not implemented"

type ipaddr = Cstruct.t

let pp_ipaddr : ipaddr Fmt.t = failwith "pp_ipaddr not implemented"

type t = IPV6.t
(* type t = Cstruct.t *)

let disconnect : t -> unit Lwt.t = failwith "disconnect not implemented"

type callback = src:ipaddr -> dst:ipaddr -> Cstruct.t -> unit Lwt.t

let input (state : t) ~(tcp : callback) ~(udp : callback)
    ~(default : proto:int -> callback) payload : unit Lwt.t =
  let src, dst = (IPV6.get_src state, IPV6.get_dst state) in
  let prt = `TCP in
  match prt with
  | `TCP -> tcp ~src ~dst payload
  | `UDP -> failwith ""
  | `ICMP -> failwith ""
  | _ -> (default ~proto:1) ~src ~dst payload

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
  failwith "write not implemented"

[%%cstruct
type pseudoheader_t = {
  src : uint8_t; [@len 16]
  dst : uint8_t; [@len 16]
  ulpl : uint8_t; [@len 4]
  zero : uint8_t; [@len 3]
  nxt_hdr : uint8_t; [@len 1]
}
[@@big_endian]]

let src t ~dst = failwith "src not implemented"

let pseudoheader t ?src:source (dst : ipaddr) (proto : Tcpip.Ip.proto) len =
  let ph = Cstruct.create sizeof_pseudoheader_t in
  let src = match source with None -> src t ~dst | Some s -> s in
  blit_pseudoheader_t_src src 0 ph;
  blit_pseudoheader_t_dst dst 0 ph;
  set_ip_hdr_t_len (Int.to_string len) 0 ph;
  set_ip_hdr_t_nh (Int.to_string 1) 0 ph;
  ph

let get_ip : t -> ipaddr list = failwith "get_ip not implemented"
let mtu : t -> dst:ipaddr -> int = failwith "mtu not implemented"

(* Can you define a struct in OCaml, for the pseudoheader *)
(* Why do you need the dst to get the src ip *)
(* What does the interanl state of the ip layer normally contain? *)
(* What is the Ndpv6.context *)
(* If i pass a structure/pointer into OCaml from C how do I interact with it? Do I define a Cstruct type? *)