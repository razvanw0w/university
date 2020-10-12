package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.Resource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.StorageRepository;

@CrossOrigin(origins = "*", allowedHeaders = "*")
@Controller
public class FileUploadController {

    @Autowired
    private final StorageRepository storageRepository;

    @Autowired
    public FileUploadController(StorageRepository storageRepository) {
        this.storageRepository = storageRepository;
    }

//    @GetMapping("/files/{filename:.+}")
//    @ResponseBody
//    public ResponseEntity<Resource> serveFile(@PathVariable String filename) {
//
//        Resource file = storageRepository.loadAsResource(filename);
//        return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION,
//                "attachment; filename=\"" + file.getFilename() + "\"").body(file);
//    }

    @PostMapping(value = "/upload",consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
    public ResponseEntity handleFileUpload(@RequestParam MultipartFile file,
//                                   RedirectAttributes redirectAttributes,
                                   @RequestParam String extraString) {

        System.out.println("Got the file");
        System.out.println("Got the string" + extraString);
        storageRepository.store(file);
        return ResponseEntity.ok().build();


//        redirectAttributes.addFlashAttribute("message",
//                "You successfully uploaded " + file.getOriginalFilename() + "!");

    }

//    @ExceptionHandler(StorageFileNotFoundException.class)
//    public ResponseEntity<?> handleStorageFileNotFound(StorageFileNotFoundException exc) {
//        return ResponseEntity.notFound().build();
//    }

}