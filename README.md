# SVG-3D-Plugin-Tool
SVG to 3D Mesh Tool Documentation
This document provides detailed information about the SVG to 3D Mesh conversion tool built for Unreal Engine. The tool allows users to import SVG files containing basic shapes and convert them into extruded 3D meshes.
Table of Contents:
Table of Contents:	1
Overview:	1
Prerequisites:	1
Installation:	1
Dependencies:	2
Usage Guide:	3
Features:	3
Technical Details:	3
Troubleshooting:	4
Limitations:	5
Future Enhancements:	5
Extended SVG Support:	5
Conclusion:	5

Overview:
The tool parses SVG files and converts supported elements into 3D meshes:
Rectangles: Converted into cuboid meshes.
Circles: Converted into cylindrical meshes with configurable segments.
Polygons: Triangulated and extruded into 3D shapes.
Supported SVG elements: <rect>, <circle>, <polygon>.
Prerequisites:
Unreal Engine 5.4.4+ (C++ project setup).
Basic knowledge of UE Editor and C++.
SVG files with pixel units (no percentage-based dimensions).
SVG elements must use explicit attributes (e.g., <rect x="10" y="20" width="30" height="40"/>).

Installation:
Launching the Tool:
Create an Editor stand alone window. (Edit > Plugins > Add > Editor stand alone window)
Reference Unreal’s documentation if help is needed. https://dev.epicgames.com/documentation/en-us/unreal-engine/slate-editor-window-quickstart-guide-for-unreal-engine 
Code Integration:
Add the provided files to your project's Source directory. 
Ensure all the classes/files are set up correctly and are implemented.

Dependencies:
Add the following modules to your Build.cs:
PublicDependencyModuleNames.AddRange(new string[] { 
    "Core", 
    "CoreUObject", 
    "Engine", 
    "Slate", 
    "SlateCore",
    "Xml",
    "DesktopPlatform",
    "ProceduralMeshComponent"
});
Compile and rebuild your project in Rider or Preferred IDE.
Usage Guide:
Import SVG File:
Click Browse for Files to select an SVG file.
Supported elements are validated automatically. Unsupported elements trigger warnings.
Convert SVG to Text:
Click Convert SVG to Text to display raw SVG data in the text box.
Parse SVG Data:
For file input: Click Extract SVG Data.
For raw text input: Paste SVG data into the text box and click Parse Custom SVG.

Generate 3D Mesh:
Click Generate to create extruded meshes for all parsed elements.
Meshes appear at the world origin (0,0,0).
Features:
Rectangle Handling:
Parameters: x, y, width, height.
Meshes are Extruded along the Z-axis (default depth: 50 units, can be changed within the code).
6 triangles for top/bottom faces, 12 for sides.
Circle Handling:
Parameters: cx, cy, r (radius).
Mesh is approximated using 32 segments.
Extruded into a cylinder with top/bottom caps.
Polygon Handling:
Parameters: points (space-separated x,y pairs).
Triangulation: Fan triangulation from the first vertex.
Mesh: Extruded with side walls.
Technical Details: 
Key Functions:
OnGenerateButtonClicked():
Iterates over parsed SVG elements.
Calls triangulation and mesh generation based on element type.
Spawns AMyMeshActor instances with generated geometry.
ProcessSVGNode(FXmlNode* Node):
Parses SVG attributes into FSVGElements.
Handles coordinate extraction for all supported elements.
Triangulate(FSVGElements& Elements):
Rectangles: Generates 4 corner vertices.
Circles: Generates perimeter vertices using trigonometric functions.
Polygons: Performs fan triangulation.
Mesh Generation:
Vertices: 2D coordinates are converted to 3D with Z-extrusion.
Triangles: Winding order ensures correct normals.
Common Troubleshooting:

Issue
Cause
Solution
"Invalid SVG File"	
Non-SVG content or malformed XML.
Validate SVG structure.
Unsupported Elements	


SVG contains <path>, <ellipse>, etc.
Remove unsupported elements or modify the tool's ProcessSVGNode to handle them.
No Meshes Generated
Incorrect path or parsing errors.
Check UE Logs for errors. Ensure SVG uses correct units.
Mesh Distortion		
Non-convex polygons or self-intersections.
Use simple, convex polygons in SVG.


Limitations:
No SVG Styling: Stroke/fill attributes are ignored.
Z-Fighting: Overlapping meshes may cause rendering issues.
Convex Polygons Only: Concave polygons triangulate incorrectly.
Fixed Extrusion Depth: Currently hard-coded to 50 units.

Future Enhancements:
UI Improvements:
Extrusion depth slider.
Real-time preview of generated meshes.
Extended SVG Support:
<path> elements.
Basic transforms (translate, rotate).
Advanced Features:
UV mapping for textures.
Material assignment per shape.
Conclusion:
This tool provides a foundational workflow for converting 2D SVG artwork into 3D geometry within Unreal Engine.
