# name of your application
APPLICATION = gnrc_stack

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Set this to 1 to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# =====================================================
# Add a static IPv6 link local address to any network interface.

# This macro allows to specify a certain link local IPv6 address to be assigned to a network interface on startup, which might be handy for testing. Note: a) a interface will keep its auto-generated link local address, too b) the address is incremented by 1, if multiple interfaces are present

# To use the macro just add it to CFLAGS in the application's Makefile, like:
# IPV6_STATIC_LLADDR ?= '"fe80::cafe:cafe:cafe:1"'
# CFLAGS += -DGNRC_IPV6_STATIC_LLADDR=$(STATIC_IPV6_LLADDR)
# =====================================================

# =====================================================
# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present

# Select default link layer devices based on board config
USEMODULE += netdev_default 
# Initialize the default devices
USEMODULE += auto_init_gnrc_netif 
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_ipv6
USEMODULE += gnrc_icmpv6_echo

# USEMODULE += gnrc_tcp
# USEMODULE += gnrc_udp
USEMODULE += gnrc_pktdump
# USEMODULE += gnrc_nettype_ipv6

USEMODULE += core_debug
# USEMODULE += netutils

# USEMODULE += gnrc_netif_single FOR OPTIMISATION
# USEMODULE += gnrc_sixloenc IF YOU WANT TO TEST 6loWPAN on Linux

USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

# =====================================================

CFLAGS += -DLOG_LEVEL=LOG_DEBUG
CFLAGS += -DCONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF=2 \
          -DGNRC_NETIF_IPV6_GROUPS_NUMOF=2 -DCONFIG_GNRC_IPV6_NIB_NUMOF=1 \
          -DCONFIG_GNRC_IPV6_NIB_OFFL_NUMOF=1 # be able to configure at least one route

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 0

include $(RIOTBASE)/Makefile.include

CFLAGS := $(subst -Werror,,$(CFLAGS))
# Set GNRC_PKTBUF_SIZE via CFLAGS if not being set via Kconfig.
ifndef CONFIG_GNRC_PKTBUF_SIZE
  CFLAGS += -DCONFIG_GNRC_PKTBUF_SIZE=512
endif

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
