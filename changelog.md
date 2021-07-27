<!DOCTYPE html>
<html>
<head>
<title> Change Log </title>
</head>
<body>

<h1><p style="text-align: center;"> <strong> Change Log </strong> </p> </h1>

<h2> 2021-07-26 </h2>
<p>#################</p>

<h3> Overall Changes </h3>
<ul> 
<li> Changed Overall Vendor Folder Structure </li>
    <ul>
    <li> Changed Vulkan Folder From <code>Vendor/include/vulkan</code> to <code>Vendor/Vulkan/include/vulkan</code> </li>
    <li> Changed GLFW Folder From <code>Vendor/include/GLFW</code> to <code>Vendor/GLFW</code> </li>
    <li> Changed GLM Folder From <code>Vendor/include/glm</code> to <code>Vendor/GLM</code> </li>
    </ul>
</ul><br>
<h3> General Fixes</h3>
<ul>
<li> Fixed missing parenthesis on glfwInit() function in window.cpp </li>
</ul><br>
<h3> Additions </h3>
<ul> 
<li> Added .gitsubmodule for GLFW and GLM libraries </li>
<li> Added GLFW to Root Level CMakeLists.txt in order to build from the submodule source code </li>
    <ul>
    <li> Added GLFW to Base Project's CMakeLists.txt as a target linking library </li>
    </ul>
<li> Added the include header <code>#include &ltvulkan/vulkan.h&gt </code> to <code>window.h</code> </li>
<li> Added the include header <code>#include "Window/window.h" </code> to <code> base.h </code> </li>    
<li> Implemented the Window Class Destructor to destroy the window and terminate GLFW </li>
<li> Added window handle from the Window class to BaseApplication class in base.h</li>
<li> Added temporary event callbacks for window movement and cursor position </li>
    <ul>
    <li>Added <code>cursor_position_callback</code> and <code>window_pos_callback</code> functions to <br><code>PollEvents()</code> which is currently called in <code>Close()</code> in window.cpp/window.h</li>
</ul><br>
<h3> Removed </h3>
<ul>
<li> Removed Pre-built libraries for GLFW in favor of building from source in CMake </li>
<li> Removed manually added cmake folders containing config packages for both glm and glfw in favor of submodule usage </li>
<li> Removed Previous code for glfw testing in main.cpp as it's now incorporated into window.cpp/base.h</li>
</ul>

</body>
</html>