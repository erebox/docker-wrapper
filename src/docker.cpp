#include <windows.h>
#include <fstream>
#include <string>

std::string readExePath(const std::string& file) { // Funzione semplice per estrarre il valore di "podman_path" da un JSON minimale
    std::ifstream f(file);
    if (!f) return "";
    std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    auto keyPos = content.find("\"podman_path\"");
    if (keyPos == std::string::npos) return "";

    auto start = content.find('"', keyPos + 13);
    if (start == std::string::npos) return "";
    auto end = content.find('"', start + 1);
    if (end == std::string::npos) return "";

    return content.substr(start + 1, end - start - 1);
}

int main(int argc, char* argv[]) {
    
    std::string podmanPath = readExePath("docker.json"); // Legge il path di podman.exe da podman.json nella stessa cartella
    if (podmanPath.empty()) {
        //MessageBoxA(NULL, "Impossibile leggere podman_path da docker.json", "Errore", MB_ICONERROR);
        //return 1;
        podmanPath = "C:\\Program Files\\RedHat\\Podman\\podman.exe";
    }

    // Costruisce la command line completa
    std::string cmd = "\"" + podmanPath + "\"";
    for (int i = 1; i < argc; ++i) {
        cmd += " \"";
        cmd += argv[i];
        cmd += "\"";
    }

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        MessageBoxA(NULL, ("Errore nell'avvio di podman.exe:\n" + podmanPath).c_str(), "Errore", MB_ICONERROR);
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD code = 0;
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return (int)code;
}
