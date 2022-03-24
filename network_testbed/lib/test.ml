open Ipaddr
open Ipaddr_cstruct.V6

let parse_ip ip_string =
  Ipaddr.of_string ip_string |> function
  | Ok res -> res
  | Error e -> ( match e with `Msg s -> failwith s)

let write_ipv6_to_cstruct ?(off = 0) ipv6 cs =
  let _ = to_cstruct ~allocator:(fun _ -> Cstruct.sub cs off 16) ipv6 in
  ()

let mock_src = "fe80::e4c0:1eff:fe53:6538" |> parse_ip |> to_v6
let mock_dst = "fe80::60e4:ecff:fea5:1b99" |> parse_ip |> to_v6

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

let mock_hdr =
  let open Cstruct in
  let hdr = create 39 in
  BE.set_uint16 hdr 0 42;
  BE.set_uint16 hdr 2 39;
  set_uint8 hdr 4 0;
  set_uint8 hdr 5 17;
  set_uint8 hdr 6 0;
  write_ipv6_to_cstruct ~off:7 mock_src hdr;
  write_ipv6_to_cstruct ~off:23 mock_dst hdr;
  hdr

[%%cstruct
type pseudoheader_t = {
  src : uint8_t; [@len 16]
  dst : uint8_t; [@len 16]
  ulpl : uint8_t; [@len 4]
  zero : uint8_t; [@len 3]
  nxt_hdr : uint8_t; [@len 1]
}
[@@big_endian]]

let mock_ph =
  let ph = Cstruct.create (16 + 16 + 8) in
  write_ipv6_to_cstruct ~off:0 mock_src ph;
  write_ipv6_to_cstruct ~off:16 mock_dst ph;
  Cstruct.set_uint8 ph 39 17;
  ph

[%%cstruct
type dummy_t = { first : uint64; [@len 1] second : uint8 [@len 1] }
[@@little_endian]]

external get_dummy : Cstruct.buffer -> int = "caml_get_pkt"