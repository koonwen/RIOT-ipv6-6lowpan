module IPV4 : sig
  (* TODO *)
end = struct
  (* TODO *)
end

module IPV6 : sig
  type t
  type ipv6_addr = Cstruct.t

  val get_src : t -> ipv6_addr
  val get_dst : t -> ipv6_addr
end = struct
  type t = Cstruct.t
  type ipv6_addr = Cstruct.t

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

  let get_src t = get_ip_hdr_t_src t
  let get_dst t = get_ip_hdr_t_dst t
end

let print_addr strct = Cstruct.to_string strct