"use strict";

const windowFuncs = {
    getAllStrokes: () => {
      fetch("http://localhost:8080/getAllKeys")
        .then(resp => resp.text())
        .then(text => JSON.parse(text))
        .then(keystrokes => {
          keystrokes.forEach(entry => {
            const dataTableBody = document.querySelector("tbody"),
              newRow = document.createElement("tr"),
              newComputer = document.createElement("td"),
              newKeyStrokes = document.createElement("td"),
              newTimestamp = document.createElement("td"),
              computerText = document.createTextNode(entry.computerName),
              keyStrokeText = document.createTextNode(entry.keystrokes),
              timeStampText = document.createTextNode(entry.timestamp);

            newComputer.appendChild(computerText);
            newKeyStrokes.appendChild(keyStrokeText);
            newTimestamp.appendChild(timeStampText);

            newRow.appendChild(newComputer);
            newRow.appendChild(newKeyStrokes);
            newRow.appendChild(newTimestamp);

            dataTableBody.appendChild(newRow);
          });
        }).catch(e => {
            throw new Error(e);
        });
    }
  };



(() => {
  window.addEventListener(
    "DOMContentLoaded",
    e => {
        const submitButton = document.querySelector("#submitBtn"),
        searchInput = document.querySelector("#searchInput"),
        dataTable = document.querySelector("#dataTable");

      submitButton.addEventListener("click", e => {
        e.preventDefault();
      });

      searchInput.addEventListener("input", e => {
        e.preventDefault();
      });

      windowFuncs.getAllStrokes();
    },
    false
  );
})();
