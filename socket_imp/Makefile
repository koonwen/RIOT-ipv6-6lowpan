# name of your application
APPLICATION = socket_imp

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Set this to 1 to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present

# Select default link layer devices based on board config
USEMODULE += netdev_default 
# Initialize the default devices specified by netdev_default
USEMODULE += auto_init_gnrc_netif 
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo
# USEMODULE += gnrc_icmpv6_error
USEMODULE += gnrc_ipv6_default

# These are the API's we need for sock API
USEMODULE += gnrc_sock_ip
# USEMODULE += gnrc_sock_tcp
# USEMODULE += gnrc_sock_udp

# USEMODULE += gnrc_netif_single FOR OPTIMISATION
# USEMODULE += gnrc_sixloenc IF YOU WANT TO TEST 6loWPAN on Linux
USEMODULE += core_debug

USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

CFLAGS += -DLOG_LEVEL=LOG_DEBUG  # disable log output
CFLAGS += -DCONFIG_GNRC_IPV6_NIB_SLAAC=1 \
          -DCONFIG_GNRC_IPV6_NIB_ARSM=1
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
