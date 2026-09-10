#include "il2cpp-config.h"

#include <stddef.h>

#include "icalls/mscorlib/System.Reflection/FieldInfo.h"

#include "il2cpp-class-internals.h"
#include "il2cpp-object-internals.h"
#include "vm/Class.h"
#include "vm/Exception.h"
#include "vm/Field.h"
#include "vm/Reflection.h"
#include "hybridclr/metadata/AOTHomologousImage.h"
#include "hybridclr/metadata/MetadataModule.h"

namespace il2cpp
{
namespace icalls
{
namespace mscorlib
{
namespace System
{
namespace Reflection
{
    static bool IsDheEquivalentDeclaringType(Il2CppClass* originalClass, Il2CppClass* logicalParent)
    {
        if (!originalClass || !logicalParent || !logicalParent->image ||
            !logicalParent->image->assembly ||
            !hybridclr::dhe::IsDheAssembly(logicalParent->image->assembly))
            return false;

        hybridclr::metadata::AOTHomologousImage* homologous =
            hybridclr::metadata::AOTHomologousImage::FindImageByAssembly(
                logicalParent->image->assembly);
        if (!homologous)
            return false;

        const Il2CppType* currentType = homologous->GetDheCurrentType(&logicalParent->byval_arg);
        if (!currentType)
            return false;
        Il2CppClass* currentClass = vm::Class::FromIl2CppType(currentType);
        for (Il2CppClass* k = originalClass; k; k = k->parent)
            if (k == currentClass)
                return true;
        return false;
    }

    Il2CppReflectionField* FieldInfo::internal_from_handle_type(intptr_t field_handle, intptr_t type_handle)
    {
        ::FieldInfo* fieldInfo = (::FieldInfo*)field_handle;
        Il2CppType* il2cppType = (Il2CppType*)type_handle;

        Il2CppClass* logicalParent = vm::Field::GetParent(fieldInfo);
        if (il2cppType == NULL)
            return vm::Reflection::GetFieldObject(logicalParent, fieldInfo);

        Il2CppClass* originalClass = vm::Class::FromIl2CppType(il2cppType);

        for (Il2CppClass* k = originalClass; k; k = k->parent)
        {
            if (k == logicalParent)
                return vm::Reflection::GetFieldObject(originalClass, fieldInfo);
            if (!k->byval_arg.valuetype && !logicalParent->byval_arg.valuetype &&
                vm::Class::FromIl2CppType(hybridclr::metadata::MetadataModule::GetDhePublicReferenceType(&k->byval_arg)) ==
                vm::Class::FromIl2CppType(hybridclr::metadata::MetadataModule::GetDhePublicReferenceType(&logicalParent->byval_arg)))
                return vm::Reflection::GetFieldObject(originalClass, fieldInfo);
        }

        // DHE may expose a physical Current field while its logical declaring
        // type remains the Base class. The managed handle API still supplies
        // the reflected Current type, so accept the homologous Current class
        // as an equivalent declaring owner.
        if (IsDheEquivalentDeclaringType(originalClass, logicalParent))
            // Preserve the reflected type supplied by FieldInfo.GetFieldFromHandle.
            // DHE has already remapped old Base objects to this Current view;
            // retaining the logical Base owner here recreates a second type
            // handle and makes RuntimeFieldInfo.GetValue reject the object.
            return vm::Reflection::GetFieldObject(originalClass, fieldInfo);

        return NULL;
    }

    Il2CppObject* FieldInfo::get_marshal_info(Il2CppObject* thisPtr)
    {
        IL2CPP_NOT_IMPLEMENTED_ICALL_NO_ASSERT(FieldInfo::get_marshal_info, "We currently don't store marshal information in metadata");
        return NULL;
    }
} /* namespace Reflection */
} /* namespace System */
} /* namespace mscorlib */
} /* namespace icalls */
} /* namespace il2cpp */
