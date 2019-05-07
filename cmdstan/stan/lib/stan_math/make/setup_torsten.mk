ifdef TORSTEN_CVS_JAC_AD
   CXXFLAGS += -DTORSTEN_CVS_JAC_AD
endif

ifdef TORSTEN_MPI
  # LIBMPI ?=
  CXXFLAGS_MPI += -DTORSTEN_MPI
  CXXFLAGS += $(CXXFLAGS_MPI)
  LDFLAGS += $(LDFLAGS_MPI)
  CC=mpicxx
  CXX=mpicxx
  # LDFLAGS_MPI ?=
endif

ifdef TORSTEN_USE_STAN_ODE
  CXXFLAGS += -DTORSTEN_USE_STAN_ODE
endif
