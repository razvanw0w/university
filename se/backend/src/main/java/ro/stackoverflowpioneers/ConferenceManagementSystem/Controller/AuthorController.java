package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.UserLoginDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Author;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.AuthorRepository;

import java.util.List;

@Controller
@RequestMapping("/author")
@CrossOrigin(origins = "http://localhost:3000")
public class AuthorController {
    @Autowired
    private AuthorRepository authorRepository;

    @GetMapping("/all")
    public @ResponseBody
    Iterable<Author> getAllAuthors() {
        return authorRepository.findAll();
    }

    @PostMapping("/add")
    public @ResponseBody
    String addAuthor(@RequestParam Integer conferenceId, @RequestParam String name, @RequestParam String affiliation,
                     @RequestParam String email, @RequestParam String webpage, @RequestParam String username, @RequestParam String password) {
        Author author = new Author(conferenceId, name, affiliation, email, webpage, username, password);
        authorRepository.save(author);
        return "Saved";
    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path = "/login")
    public @ResponseBody
    UserLoginDTO login(@RequestParam String email, @RequestParam String password) {
        List<Author> users = (List<Author>) authorRepository.findAll();
        boolean logged = false;
        Author foundUser = null;
        for (Author user : users) {
            if (user.getPassword().equals(password) && user.getEmail().equals(email)) {
                foundUser = user;
                logged = true;
                break;
            }
        }
        if (!logged)
            return null;
        return new UserLoginDTO(foundUser.getId(), foundUser.getConferenceId());
    }
}
