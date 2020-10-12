package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Abstract;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.AbstractRepository;

import java.util.Optional;

@Controller
@RequestMapping(path="/abstracts")
public class AbstractController {
    @Autowired
    private AbstractRepository abstractRepository;

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewAbstract() {
        Abstract abs = new Abstract();
        abstractRepository.save(abs);
        return "Abstract saved!";
    }

    @PostMapping(path = "/delete")
    public @ResponseBody String deleteAbstract(@RequestParam Integer id) {
        Optional<Abstract> abs = abstractRepository.findById(id);
        if(!abs.isPresent()){
            return "Abstract with this ID doesn't exist";
        }
        abstractRepository.deleteById(id);
        return "Deleted";
    }

    @PostMapping(path = "/update")
    public @ResponseBody String updateAbstract(@RequestParam Integer id, @RequestParam String file){
        Optional<Abstract> abs = abstractRepository.findById(id);
        if(!abs.isPresent()){
            return "Abstract with this ID doesn't exist";
        }
        Abstract abstr = new Abstract(file);
        abstr.setId(id);
        abstractRepository.save(abstr);
        return "Updated";
    }

    @GetMapping(path = "/all")
    public @ResponseBody Iterable<Abstract> getAllAbstracts() {
        return abstractRepository.findAll();
    }
}
