<h1 align="center">🎬 GIF-Maker </h1>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c&logoColor=white" />
  <img src="https://img.shields.io/badge/Windows-10-blue?style=flat-square&logo=windows&logoColor=white" />
  <img src="https://www.vectorlogo.zone/logos/opencv/opencv-icon.svg" />
  <img src="https://img.shields.io/badge/Author-Ido_Redid-blue?style=flat-square" />
</p>

---

## 📝 Description

Final project for Magshimim's first year (Israel National Cyber Education Program).  
This program allows the user to **manage movies/gifs** with frame-level control and grayscale filters.

---

## ⚙️ Features

- **Frame Management**
  - Add a frame
  - Remove a frame
  - Change the location of a frame (index)
  - Change duration of a specific frame
  - Change duration of all frames at once
  - List all frames with info

- **Playback**
  - Play the movie forward
  - Play the movie in reverse

- **Project Management**
  - Change working directory
  - Save/load previous projects

---

## 🛠️ Dependencies

- Windows 10  
- OpenCV (required if building from source, included as DLL in release)  

// Example: Loading a project file
loadProject("examples/example_project.gproj");
