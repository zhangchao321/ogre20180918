/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef __MemoryAllocatorConfig_H__
#define __MemoryAllocatorConfig_H__

#include "OgreAlignedAllocator.h"

namespace Ogre
{
    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup General
    *  @{
    */

    /** A set of categories that indicate the purpose of a chunk of memory
    being allocated. 
    These categories will be provided at allocation time in order to allow
    the allocation policy to vary its behaviour if it wishes. This allows you
    to use a single policy but still have variant behaviour. The level of 
    control it gives you is at a higher level than assigning different 
    policies to different classes, but is the only control you have over
    general allocations that are primitive types.
    */
    enum MemoryCategory
    {
        /// General purpose
        MEMCATEGORY_GENERAL = 0,
        /// Geometry held in main memory
        MEMCATEGORY_GEOMETRY = 1, 
        /// Animation data like tracks, bone matrices
        MEMCATEGORY_ANIMATION = 2, 
        /// Nodes, control data
        MEMCATEGORY_SCENE_CONTROL = 3,
        /// Scene object instances
        MEMCATEGORY_SCENE_OBJECTS = 4,
        /// Other resources
        MEMCATEGORY_RESOURCE = 5,
        /// Scripting
        MEMCATEGORY_SCRIPTING = 6,
        /// Rendersystem structures
        MEMCATEGORY_RENDERSYS = 7,

        
        // sentinel value, do not use 
        MEMCATEGORY_COUNT = 8
    };
    /** @} */
    /** @} */

}

namespace Ogre
{
    class AllocPolicy {};
    // this is a template, mainly so swig does not pick it up
    template<int Category = MEMCATEGORY_GENERAL> class AllocatedObject {};

    // Useful shortcuts
    using GeneralAllocPolicy =AllocPolicy;
	using GeometryAllocPolicy =AllocPolicy;
	using AnimationAllocPolicy =AllocPolicy;
	using SceneCtlAllocPolicy =AllocPolicy;
	using SceneObjAllocPolicy =AllocPolicy;
	using ResourceAllocPolicy =AllocPolicy ;
	using ScriptingAllocPolicy =AllocPolicy;
	using RenderSysAllocPolicy =AllocPolicy;

    // Now define all the base classes for each allocation
	using GeneralAllocatedObject =AllocatedObject<>;
	using GeometryAllocatedObject =AllocatedObject<>;
	using AnimationAllocatedObject =AllocatedObject<>;
	using SceneCtlAllocatedObject =AllocatedObject<>;
	using SceneObjAllocatedObject =AllocatedObject<>;
	using ResourceAllocatedObject =AllocatedObject<>;
	using ScriptingAllocatedObject =AllocatedObject<>;
	using RenderSysAllocatedObject =AllocatedObject<>;


    // Per-class allocators defined here
    // NOTE: small, non-virtual classes should not subclass an allocator
    // the virtual function table could double their size and make them less efficient
    // use primitive or STL allocators / deallocators for those
	using AbstractNodeAlloc =ScriptingAllocatedObject;
	using AnimableAlloc =AnimationAllocatedObject;
	using AnimationAlloc =AnimationAllocatedObject;
	using ArchiveAlloc =GeneralAllocatedObject;
	using BatchedGeometryAlloc =GeometryAllocatedObject;
	using BufferAlloc =RenderSysAllocatedObject;
	using CodecAlloc =GeneralAllocatedObject;
	using CompositorInstAlloc =ResourceAllocatedObject;
	using ConfigAlloc =GeneralAllocatedObject;
	using ControllerAlloc =GeneralAllocatedObject;
	using DebugGeomAlloc =GeometryAllocatedObject;
	using DynLibAlloc =GeneralAllocatedObject;
	using EdgeDataAlloc =GeometryAllocatedObject;
	using FactoryAlloc =GeneralAllocatedObject;
	using FXAlloc =SceneObjAllocatedObject;
	using ImageAlloc =GeneralAllocatedObject;
	using IndexDataAlloc =GeometryAllocatedObject;
	using LogAlloc =GeneralAllocatedObject;
	using MovableAlloc =SceneObjAllocatedObject;
	using NodeAlloc =SceneCtlAllocatedObject;
	using OverlayAlloc =SceneObjAllocatedObject;
	using GpuParamsAlloc =RenderSysAllocatedObject;
	using PassAlloc =ResourceAllocatedObject;
	using PatchAlloc =GeometryAllocatedObject;
	using PluginAlloc =GeneralAllocatedObject;
	using ProfilerAlloc =GeneralAllocatedObject;
	using ProgMeshAlloc =GeometryAllocatedObject;
	using RenderQueueAlloc =SceneCtlAllocatedObject;
	using RenderSysAlloc =RenderSysAllocatedObject;
	using RootAlloc =GeneralAllocatedObject;
	using ResourceAlloc =ResourceAllocatedObject;
	using SerializerAlloc =GeneralAllocatedObject;
	using SceneMgtAlloc =SceneCtlAllocatedObject;
	using ScriptCompilerAlloc =ScriptingAllocatedObject;
	using ScriptTranslatorAlloc =ScriptingAllocatedObject;
	using ShadowDataAlloc =SceneCtlAllocatedObject;
	using StreamAlloc =GeneralAllocatedObject;
	using SubEntityAlloc =SceneObjAllocatedObject;
	using SubMeshAlloc =ResourceAllocatedObject;
	using TechniqueAlloc =ResourceAllocatedObject;
	using TimerAlloc =GeneralAllocatedObject;
	using TextureUnitStateAlloc =ResourceAllocatedObject;
	using UtilityAlloc =GeneralAllocatedObject;
	using VertexDataAlloc =GeometryAllocatedObject;
	using ViewportAlloc =RenderSysAllocatedObject;
	using LodAlloc =SceneCtlAllocatedObject;
	using FileSystemLayerAlloc =GeneralAllocatedObject;
	using StereoDriverAlloc =GeneralAllocatedObject;

    // Containers (by-value only)
    // Will  be of the form:
    // typedef STLAllocator<T, DefaultAllocPolicy, Category> TAlloc;
    // for use in std::vector<T, TAlloc> 
    


}

// define macros 

/** \addtogroup Core
*  @{
*/
/** \addtogroup General
*  @{
*/

/// Allocate a block of raw memory, and indicate the category of usage
#   define OGRE_MALLOC(bytes, category) (void*)new char[bytes]
/// Allocate a block of memory for a primitive type, and indicate the category of usage
#   define OGRE_ALLOC_T(T, count, category) (T*)new char[(count) * sizeof(T)]
/// Free the memory allocated with OGRE_MALLOC or OGRE_ALLOC_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE(ptr, category) delete[] (char*)ptr

/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#   define OGRE_NEW_T(T, category) new T
/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T(T, count, category) new T[count]
/// Free the memory allocated with OGRE_NEW_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T(ptr, T, category) delete ptr
/// Free the memory allocated with OGRE_NEW_ARRAY_T. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T(ptr, T, count, category) delete[] ptr

// aligned allocation
/// Allocate a block of raw memory aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_MALLOC_SIMD(bytes, category) ::Ogre::AlignedMemory::allocate(bytes)
/// Free the memory allocated with either OGRE_MALLOC_SIMD or OGRE_ALLOC_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_SIMD(ptr, category) ::Ogre::AlignedMemory::deallocate((void*)ptr)

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
#   define OGRE_NEW new 
#   define OGRE_DELETE delete

/** @} */
/** @} */

#endif
