#include "Beam/Python/Routines.hpp"
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "Beam/Routines/Routine.hpp"
#include "Beam/Routines/RoutineException.hpp"
#include "Beam/Routines/RoutineHandler.hpp"
#include "Beam/Routines/RoutineHandlerGroup.hpp"

using namespace Beam;
using namespace Beam::Python;
using namespace Beam::Routines;
using namespace pybind11;

void Beam::Python::ExportBaseAsync(pybind11::module& module) {
  auto outer = class_<BaseAsync>(module, "BaseAsync");
  enum_<BaseAsync::State>(outer, "State")
    .value("PENDING", BaseAsync::State::PENDING)
    .value("COMPLETE", BaseAsync::State::COMPLETE)
    .value("EXCEPTION", BaseAsync::State::EXCEPTION);
}

void Beam::Python::ExportBaseEval(pybind11::module& module) {
  class_<BaseEval>(module, "BaseEval");
}

void Beam::Python::ExportRoutineHandler(pybind11::module& module) {
  class_<RoutineHandler>(module, "RoutineHandler")
    .def(init())
    .def(init<Routine::Id>())
    .def("__del__",
      [] (RoutineHandler& self) {
        self.Wait();
      }, call_guard<gil_scoped_release>())
    .def_property_readonly("id", &RoutineHandler::GetId)
    .def("detach", &RoutineHandler::Detach)
    .def("wait", &RoutineHandler::Wait, call_guard<gil_scoped_release>());
  module.def("flush_pending_routines", &FlushPendingRoutines,
    call_guard<gil_scoped_release>());
}

void Beam::Python::ExportRoutineHandlerGroup(pybind11::module& module) {
  class_<RoutineHandlerGroup>(module, "RoutineHandlerGroup")
    .def(init())
    .def("__del__",
      [] (RoutineHandlerGroup& self) {
        self.Wait();
      }, call_guard<gil_scoped_release>())
    .def("add", static_cast<void (RoutineHandlerGroup::*)(Routine::Id)>(
      &RoutineHandlerGroup::Add))
    .def("add",
      [] (RoutineHandlerGroup& self, RoutineHandler* handler) {
        self.Add(std::move(*handler));
      })
    .def("spawn", &RoutineHandlerGroup::Spawn<const std::function<void ()>&>)
    .def("wait", &RoutineHandlerGroup::Wait,
      call_guard<gil_scoped_release>());
}

void Beam::Python::ExportRoutines(pybind11::module& module) {
  auto submodule = module.def_submodule("routines");
  ExportBaseAsync(submodule);
  ExportBaseEval(submodule);
  ExportRoutineHandler(submodule);
  ExportRoutineHandlerGroup(submodule);
  ExportAsync<object>(submodule, "");
  ExportEval<object>(submodule, "");
  submodule.def("spawn",
    static_cast<Routine::Id (*)(const std::function<void ()>&)>(&Spawn));
  submodule.def("wait", &Wait, call_guard<gil_scoped_release>());
  register_exception<RoutineException>(submodule, "RoutineException");
}
