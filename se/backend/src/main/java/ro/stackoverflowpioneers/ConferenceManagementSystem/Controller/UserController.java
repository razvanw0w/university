package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Conference;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ConferenceUser;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.UserRepository;

import java.util.List;
import java.util.Optional;

@Controller
@RequestMapping("/users")
public class UserController {
    @Autowired
    private UserRepository userRepository;

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewUser(@RequestParam String name, @RequestParam String affiliation, @RequestParam String email, @RequestParam String webpage, @RequestParam String username, @RequestParam String password) {
        ConferenceUser user = new ConferenceUser(name, affiliation, email, webpage, username, password);
        userRepository.save(user);
        return "User saved";
    }

    @PostMapping(path = "/delete")
    public @ResponseBody String deleteUser(@RequestParam Integer id) {
        Optional<ConferenceUser> user = userRepository.findById(id);
        if(!user.isPresent()){
            return "User with this ID doesn't exist";
        }
        userRepository.deleteById(id);
        return "Deleted";
    }

    @PostMapping(path = "/update")
    public @ResponseBody String updateUser(@RequestParam Integer id, @RequestParam String name,
                                           @RequestParam String affiliation, @RequestParam String email,
                                           @RequestParam String webpage, @RequestParam String username,
                                           @RequestParam String password) {
        Optional<ConferenceUser> user = userRepository.findById(id);
        if(!user.isPresent()) {
            return "User with this ID doesn't exist";
        }
        ConferenceUser newUser = new ConferenceUser(name, affiliation, email, webpage, username, password);
        newUser.setId(id);
        userRepository.save(newUser);
        return "Updated";
    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path = "/all")
    public @ResponseBody
    Iterable<ConferenceUser> getAllUsers() {
        return userRepository.findAll();
    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path="/login")
    public @ResponseBody String login(@RequestParam String email, @RequestParam String password){
        List<ConferenceUser> users = (List<ConferenceUser>) userRepository.findAll();
        boolean logged = false;
        for (ConferenceUser user : users) {
            if (user.getPassword().equals(password) && user.getEmail().equals(email)) {
                logged = true;
                break;
            }
        }
        if(!logged)
            return "Bad info!";
        return "Logged in!";
    }
}
