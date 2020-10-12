package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Room;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.RoomRepository;

@Controller
@RequestMapping("/rooms")
public class RoomController {
    @Autowired
    private RoomRepository roomRepository;

    //TODO: delete and update

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewRoom(@RequestParam Integer capacity, @RequestParam Integer number){
        Room room = new Room();
        room.setCapacity(capacity);
        room.setNumber(number);
        roomRepository.save(room);
        return "Saved";
    }

    @GetMapping(path = "/all")
    public @ResponseBody Iterable<Room> getAllRooms(){
        return roomRepository.findAll();
    }


}
